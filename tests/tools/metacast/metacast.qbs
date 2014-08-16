import qbs

Product {
    name: "tst_metacast"
    consoleApplication: true
    type: [
        "application"
    ]
    files: [
        "*.h",
        "*.cpp"
    ]

    Depends {
        name: "cpp"
    }

    cpp.includePaths: [
        "../../../src"
    ]

    Properties {
        condition: qbs.toolchain.contains("gcc") || qbs.toolchain.contains("mingw")
        cpp.cxxFlags: [
            "-std=c++11",
            "-mtune=native",
            "-march=native",
            "-o3",
            "-funroll-loops",
            "-flto"
        ]
    }

    Depends {
        name: "Qt"
        submodules: [
            "testlib"
        ]
    }
}
