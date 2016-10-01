#pragma once

#include <string>

#include "filesystem/path.h"

namespace services {
    class ResourceLocator {
    public:
        virtual std::string pathTo(std::string resc) = 0;
    };

    class FilesystemResourceLocator : public ResourceLocator {
    public:
        virtual std::string pathTo(std::string resc);

        static filesystem::path backtrackToBasedir(filesystem::path cwd);

        filesystem::path basedir;
    };

    class NullResourceLocator : public ResourceLocator {
        virtual std::string pathTo(std::string resc) { return ""; }
    };
}
