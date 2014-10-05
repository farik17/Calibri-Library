import qbs

Product {
    name: "tst_bytearray"
    consoleApplication: true
    type: [
        "application"
    ]
    files: [
        "*.h",
        "*.cpp"
    ]

    Depends {
        name: "Qt"
        submodules: [
            "testlib"
        ]
    }

    Depends {
        name: "cpp"
    }

    cpp.includePaths: [
        "../../../src"
    ]
    cpp.libraryPaths: [
        buildDirectory
    ]
    cpp.dynamicLibraries: qbs.buildVariant === "debug"
                          ? [
                                "calibrid"
                            ]
                          : [
                                "calibri"
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
}
