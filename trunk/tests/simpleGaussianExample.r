simpleGaussianExample <- hugin.domain()

add.node(simpleGaussianExample, "X", kind = "continuous")
add.node(simpleGaussianExample, "Y", kind = "continuous")
add.node(simpleGaussianExample, "Z", kind = "continuous")

add.edge(simpleGaussianExample, "Y", "X")
add.edge(simpleGaussianExample, "Z", "Y")

X.table <- get.table(simpleGaussianExample, "X")
X.table[, 2] <- c(0, 1)
set.table(simpleGaussianExample, "X", X.table)

Y.table <- get.table(simpleGaussianExample, "Y")
Y.table[, 2] <- c(0, 1, 1)
set.table(simpleGaussianExample, "Y", Y.table)

Z.table <- get.table(simpleGaussianExample, "Z")
Z.table[, 2] <- c(0, 1, 1)
set.table(simpleGaussianExample, "Z", Z.table)

compile(simpleGaussianExample)
set.finding(simpleGaussianExample, "Z", 1.5)
propagate(simpleGaussianExample)

X.belief <- get.belief(simpleGaussianExample, "X")
Y.belief <- get.belief(simpleGaussianExample, "Y")

rm(simpleGaussianExample, X.table, Y.table, Z.table)


