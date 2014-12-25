import qbs

Product {
    name: "Source"
    targetName: project.libraryName
    destinationDirectory: project.libraryDestinationDirectory
    type: [
        "staticlibrary",
        "dynamiclibrary"
    ]

    Depends {
        name: "cpp"
    }

    cpp.includePaths: {
        var includePaths = [
                    project.libraryDirectory
                ]

        if (project.opensslIncludeDirectory !== undefined)
            includePaths.push(project.opensslIncludeDirectory)

        return includePaths
    }
    cpp.libraryPaths: {
        var libraryPaths = []

        if (project.opensslLibraryDirectory !== undefined)
            libraryPaths.push(project.opensslLibraryDirectory)

        return libraryPaths
    }
    cpp.dynamicLibraries: {
        var dynamicLibraries = []

        if (qbs.targetOS.contains("windows"))
            dynamicLibraries.push("eay32")
        else if (qbs.targetOS.contains("linux"))
            dynamicLibraries.push("crypto")

        return dynamicLibraries
    }
    cpp.cxxFlags: project.compilerFlags

    Group {
        name: "Global"
        prefix: "global/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        name: "Io"
        prefix: "io/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        name: "Tools"
        prefix: "tools/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        name: "Thread"
        prefix: "thread/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        name: "Signals"
        prefix: "signals/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }

    Group {
        name: "Crypto"
        prefix: "crypto/"
        files: [
            "*.h",
            "*.cpp"
        ]
    }
}
