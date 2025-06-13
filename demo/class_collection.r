library(RHugin)

# Create a class collection
cc <- hugin.class.collection()

# Make main class
main <- hugin.class(cc)
set.class.name(main, "main")

# Create a class
class <- hugin.class(cc)
set.class.name(class, "fruits")

# Get class name
get.class.name(class)

# Get class by name 
fruits_class <- hugin.class.collection.get.class.by_name(cc, "fruits")

# Add node to class
add.class.node(fruits_class, "apple", states = c("yes", "no", "maybe"))
add.class.node(fruits_class, "banana", states = c("yes", "no", "maybe"))
add.class.node(fruits_class, "pear", states = c("yes", "no", "maybe"))

add.edge(fruits_class, "pear", "apple")
add.edge(fruits_class, "pear", "banana")

# Add node to inputs of its home class
set.node.input(fruits_class, c("apple", "banana"))

# Get inputs of class
inputs <- get.class.inputs(class)

# Add node to output of its home class
set.node.output(fruits_class, c("pear"))

# Get outputs of class
outputs <- get.class.outputs(class)

# Make instance of class
hugin.class.instance(main, class, "fruit_box1")
hugin.class.instance(main, class, "fruit_box2")

write.rhcc(cc, "main.oobn", "oobn")








