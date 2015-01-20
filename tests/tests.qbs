import qbs

Project {
    name: "Tests"
    references: [
        "io/io.qbs",
        "tools/tools.qbs",
        "crypto/crypto.qbs",
        "algorithm/algorithm.qbs"
    ]
}
