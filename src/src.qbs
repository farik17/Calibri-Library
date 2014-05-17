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
        "tools",
        "math"
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

    Group {
        name: "global"
        prefix: "global/"
        files: [
            "*.h"
        ]
    }

    Group {
        name: "io"
        prefix: "io/"
        files: [
            "*.h"
        ]
    }

    Group {
        name: "tools"
        prefix: "tools/"
        files: [
            "*.h"
        ]
    }
}
