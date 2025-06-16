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

# Make input class
input_class <- hugin.class(cc)
set.class.name(input_class, "fruit_in")
add.class.node(input_class, "apple", states = c("yes", "no", "maybe"))
set.node.output(input_class, "apple")

hugin.class.instance(main, input_class, "fruits_in")

add.class.node(main, "is_fruit", states = c("yes", "no"))
add.edge(main, "is_fruit", "fruit_box1_pear")

set.instance.input(main, "fruits_in_apple", "fruit_box1.apple")

write.rhcc(cc, "main.oobn", "oobn")








