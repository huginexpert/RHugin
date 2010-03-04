simple <- hugin.domain()

add.node(simple, "X", kind = "continuous")
add.node(simple, "Y", kind = "continuous")
add.node(simple, "Z", kind = "continuous")

add.edge(simple, "Y", "X")
add.edge(simple, "Z", "Y")

X.table <- get.table(simple, "X")
X.table[["Value"]] <- c(0, 1)
set.table(simple, "X", X.table)

Y.table <- get.table(simple, "Y")
Y.table[["Value"]] <- c(0, 1, 1)
set.table(simple, "Y", Y.table)

Z.table <- get.table(simple, "Z")
Z.table[["Value"]] <- c(0, 1, 1)
set.table(simple, "Z", Z.table)


