import qbs

Project {
    name: "Algorithms"
    references: [
        "split/split.qbs",
        "trim/trim.qbs",
        "simplify/simplify.qbs",
        "join/join.qbs"
    ]
}
