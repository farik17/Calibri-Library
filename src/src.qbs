import qbs

Product {
    name: qbs.buildVariant === "debug" ? "calibrid" : "calibri"
    type: [
        "staticlibrary",
        "dynamiclibrary"
    ]

    Depends {
        name: "cpp"
    }

    cpp.includePaths: [
        "global",
        "io",
        "tools"
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
}
