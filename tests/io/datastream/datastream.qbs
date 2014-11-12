import qbs

Product {
    name: "DataStreamTest"
    targetName: "tst_datastream"
    consoleApplication: true
    type: [
        "application"
    ]
    files: [
        "*.h",
        "*.cpp"
    ]
    destinationDirectory: project.sourceDirectory.concat("/bin")

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
        project.sourceDirectory.concat("/lib")
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
