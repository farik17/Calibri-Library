import qbs

Project {
    name: "Tests"
    references: [
        "io/io.qbs",
        "tool/tool.qbs",
        "crypto/crypto.qbs",
        "algorithm/algorithm.qbs",
        "signal/signal.qbs"
    ]
}
