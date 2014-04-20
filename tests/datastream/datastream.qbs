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
        "../../src",
        "../../src/global",
        "../../src/io"
    ]

    cpp.cxxFlags: [
        "-std=c++11"
    ]

    Depends {
        name: "Qt"
        submodules: [
            "test"
        ]
    }
}
