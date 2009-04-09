set.seed(5)
TestNetwork <- hugin.domain()

add.node(TestNetwork, "labeled", states = c("state1", "state2"))
add.node(TestNetwork, "numbered", subtype = "numbered", states = 0:1)
add.node(TestNetwork, "boolean", subtype = "boolean")
add.node(TestNetwork, "interval", subtype = "interval", states = (0:2)/2)
add.node(TestNetwork, "child", states = c("x", "y"))
add.edge(TestNetwork, "child", c("labeled", "numbered", "boolean", "interval"))

x <- get.table(TestNetwork, "child")
x$Freq <- sample(5:10, 32, TRUE)
set.table(TestNetwork, "child", x)


