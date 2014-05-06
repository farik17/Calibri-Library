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
    cpp.cxxFlags: [
        "-std=c++11"
    ]

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

    Group {
        name: "math"
        prefix: "math/"
        files: [
            "*.h"
        ]
    }
}
