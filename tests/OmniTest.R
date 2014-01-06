library(RHugin)

options.error <- options("error")$error
options(error = expression(NULL))


  ## 2. Nodes and domains ##

d <- hugin.domain()
add.node(d, "one")

# Error: "one" is already in the domain
add.node(d, "one")

d2 <- clone.domain(d)

clone.node(d, "one", "two")

add.edge(d, "two", "one")

# Error: "three" is not in the domain
delete.edge(d, "one", "three")

get.children(d, "one")

get.edges(d)

get.nodes(d)

get.parents(d, "two")










options(error = options.error)

