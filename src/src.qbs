import qbs

Product {
    name: "Source"
    targetName: qbs.buildVariant === "debug"
                ? "calibrid"
                : "calibri"
    type: [
        "staticlibrary",
        "dynamiclibrary"
    ]
    destinationDirectory: project.sourceDirectory.concat("/lib")

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
        name: "Global"
        prefix: "global/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        name: "Io"
        prefix: "io/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        name: "Tools"
        prefix: "tools/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        name: "Thread"
        prefix: "thread/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        name: "Signals"
        prefix: "signals/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        condition: qbs.targetOS.contains("windows")
                   ? qbs.getEnv("OPENSSL_PATH") !== undefined
                   : true
        name: "Crypto"
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
