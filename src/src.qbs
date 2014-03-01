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
        "io"
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
}
