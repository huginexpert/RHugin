set.seed(5)
test <- hugin.domain()

add.node(test, "labeled", states = c("state1", "state2"))
add.node(test, "numbered", subtype = "numbered", states = 0:1)
add.node(test, "boolean", subtype = "boolean")
add.node(test, "interval", subtype = "interval", states = (0:2)/2)
add.node(test, "child", states = c("x", "y"))
add.edge(test, "child", c("labeled", "numbered", "boolean", "interval"))

x <- get.table(test, "child")
x$Freq <- sample(5:10, 32, TRUE)
set.table(test, "child", x)


