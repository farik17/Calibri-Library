import qbs

Product {
    name: "MetaCastTest"
    targetName: "tst_metacast"
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
