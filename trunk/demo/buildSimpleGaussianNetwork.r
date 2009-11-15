simpleGaussianExample <- hugin.domain()

add.node(simpleGaussianExample, "X", kind = "continuous")
add.node(simpleGaussianExample, "Y", kind = "continuous")
add.node(simpleGaussianExample, "Z", kind = "continuous")

add.edge(simpleGaussianExample, "Y", "X")
add.edge(simpleGaussianExample, "Z", "Y")

X.table <- get.table(simpleGaussianExample, "X")
X.table[["Value"]] <- c(0, 1)
set.table(simpleGaussianExample, "X", X.table)

Y.table <- get.table(simpleGaussianExample, "Y")
Y.table[["Value"]] <- c(0, 1, 1)
set.table(simpleGaussianExample, "Y", Y.table)

Z.table <- get.table(simpleGaussianExample, "Z")
Z.table[["Value"]] <- c(0, 1, 1)
set.table(simpleGaussianExample, "Z", Z.table)


