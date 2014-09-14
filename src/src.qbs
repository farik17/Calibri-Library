import qbs

Product {
    name: qbs.buildVariant === "debug"
          ? "calibrid"
          : "calibri"
    type: [
        "staticlibrary",
        "dynamiclibrary"
    ]

    Depends {
        name: "cpp"
    }

    cpp.includePaths: [
        "."
    ]

    Properties {
        condition: qbs.toolchain.contains("gcc") || qbs.toolchain.contains("mingw")

        cpp.cxxFlags: qbs.buildVariant === "debug"
                      ? [
                            "-std=c++11"
                        ]
                      : [
                            "-std=c++11",
                            "-o3",
                            "-funroll-loops",
                            "-flto",
                            "-mtune=native",
                            "-march=native"
                        ]
    }

    Group {
        name: "global"
        prefix: "global/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        name: "io"
        prefix: "io/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        name: "tools"
        prefix: "tools/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        condition: qbs.targetOS.contains("windows")
                   ? qbs.getEnv("OPENSSL_PATH") !== undefined
                   : true
        name: "crypto"
        prefix: "crypto/"
        files: [
            "*.h",
            "*.cpp"
        ]

        cpp.includePaths: {
            var includePaths = outer

            if (qbs.targetOS.contains("windows"))
                includePaths.push(qbs.getEnv("OPENSSL_PATH") + "/include")

            return includePaths
        }
        cpp.libraryPaths: {
            var libraryPaths = outer

            if (qbs.targetOS.contains("windows"))
                libraryPaths.push(qbs.getEnv("OPENSSL_PATH"))

            return libraryPaths
        }
        cpp.dynamicLibraries: {
            var dynamicLibraries = outer

            if (qbs.targetOS.contains("windows"))
                dynamicLibraries.push("eay32")

            return dynamicLibraries
        }
    }
}
