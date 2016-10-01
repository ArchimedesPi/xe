#include "resources.h"

#include <iostream>

namespace services {
    std::string FilesystemResourceLocator::pathTo(std::string resource) {
        return (basedir/filesystem::path(resource)).str();
    }

    filesystem::path FilesystemResourceLocator::backtrackToBasedir(filesystem::path cwd) {
        filesystem::path path = cwd;
        for (int i=0; i<3; i++) {
            if (path.filename() == "xe") {
                return path;
            }
            path = path.parent_path();
        }
        std::cerr << "Could not find basedir within 3 parents of " << cwd << '\n';
    }
}
