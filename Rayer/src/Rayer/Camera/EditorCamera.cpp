#include <algorithm>

#include <Rayer/Core/Application.h>
#include "EditorCamera.h"
#include <Rayer/Core/Input.h>

namespace Rayer {

	EditorCamera::EditorCamera(float fov, float aspect_ratio, float near_plane, float far_plane) : m_AspectRatio{ aspect_ratio },
		m_Fov{ fov },
		m_NearPlane{ near_plane },
		m_FarPlane{ far_plane },
		Camera(glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane))
	{

		UpdateView();

	}


	void EditorCamera::OnEvent(Event& event) {

		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseScrolledEvent>(RAYER_BIND_EVENT_FN(EditorCamera::OnMouseScroll));

	}

	float EditorCamera::RotationSpeed() const
	{
		return 0.8f;
	}

	void EditorCamera::OnUpdate() {

		const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
		glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
		m_InitialMousePosition = mouse;


		if (Input::IsKeyPressed(Key::LeftAlt))
		{
			
			if (Input::IsMouseButtonPressed(Mouse::ButtonLeft)) {
				
				MouseRotate(delta);
			}
			else if (Input::IsMouseButtonPressed(Mouse::ButtonRight)) {
				
				MouseZoom(delta.y);
			}
		}


		if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
		{
			
			MousePan(delta);
		}

	
		

		UpdateView();

	}

	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}


	void EditorCamera::MousePan(const glm::vec2& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		m_FocalPoint += GetRightDirection() * -delta.x * xSpeed * m_Distance;
		m_FocalPoint += -GetUpDirection() * delta.y * ySpeed * m_Distance;
	}


	void EditorCamera::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * RotationSpeed();
		m_Pitch += delta.y * RotationSpeed();
	}

	void EditorCamera::UpdateView() {

		// m_Yaw = m_Pitch = 0.0f; // Lock the camera's rotation
		m_Position = CalculatePosition();

		glm::quat orientation = GetOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);


	}

	void EditorCamera::UpdateProjection() {

		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearPlane, m_FarPlane);

	}

	float EditorCamera::ZoomSpeed() const {

		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); // max speed = 100
		return speed;

	}

	void EditorCamera::MouseZoom(float delta) {

		m_Distance -= delta * ZoomSpeed();
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}

	}

	////////////////////////////////////////////////////////
	//                 Callbacks
	////////////////////////////////////////////////////////

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& event) {

		#ifdef RAYER_DEBUG
		std::cout <<event.ToString()<< std::endl;
		#endif // RAYER_DEBUG


		float delta = event.GetYOffset() * 0.1f;

		MouseZoom(delta);
		UpdateView();
		return false;


	}
	////////////////////////////////////////////////////////


	glm::vec3 EditorCamera::GetUpDirection() const {

		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));

	}

	glm::vec3 EditorCamera::GetRightDirection() const {

		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));

	}

	glm::vec3 EditorCamera::GetForwardDirection() const{
		
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));

	}


	glm::vec3 EditorCamera::CalculatePosition() const {

		return m_FocalPoint - GetForwardDirection() * m_Distance;

	}

	glm::quat EditorCamera::GetOrientation() const{

		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));

	}


	void EditorCamera::SetViewportSize(float width, float height) {

		m_ViewportWidth = width;
		m_ViewportHeight = height;
		UpdateProjection();

	}

}