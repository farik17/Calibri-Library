import qbs

Product {
    name: "tst_datastream"
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
        "../../../src",
        "../../../src/global",
        "../../../src/io"
    ]

    Properties {
        condition: qbs.toolchain.contains("gcc") || qbs.toolchain.contains("mingw")
        cpp.cxxFlags: [
            "-std=c++11",
            "-mtune=native",
            "-march=native",
            "-o3",
            "-funroll-loops"
        ]
    }

    Depends {
        name: "Qt"
        submodules: [
            "testlib"
        ]
    }
}
