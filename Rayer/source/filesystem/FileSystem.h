#pragma once
#include "rpch.h"

namespace fs = std::filesystem;

namespace Rayer {

	class RayerFileSystem {

	public:

		

		virtual std::string GetSolutionDirectory(const std::string& path = fs::current_path().string());
		virtual std::string ReadFileToString(const std::string& path);

		

		static RayerFileSystem& getInstance() {

			return instance;
		}

		RayerFileSystem(const RayerFileSystem&) = delete;
		RayerFileSystem& operator=(const RayerFileSystem&) = delete;
			

	private:

		

		static RayerFileSystem instance;

		RayerFileSystem();
		

	};


}