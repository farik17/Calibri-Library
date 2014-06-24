import qbs

Product {
    name: "tst_meta_cast"
    consoleApplication: true
    type: [
        "application"
    ]
    files: [
        "*.cpp"
    ]

    Depends {
        name: "cpp"
    }

    cpp.includePaths: [
        "../../../src/global",
        "../../../src/io",
        "../../../src/tools"
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
