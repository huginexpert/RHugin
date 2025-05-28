library(RHugin)

# Create a class collection
cc <- hugin.class.collection()

# Create a class
class <- hugin.class(cc)

# Set class name
set.class.name(class, "fruits")

# Get class name
get.class.name(class)

# Get class by name 
fruits_class <- hugin.class.collection.get.class.by_name(cc, "fruits")

# Add node to class
add.class.node(fruits_class, "apple", states = c("yes", "no", "maybe"))
add.class.node(fruits_class, "banana", states = c("yes", "no", "maybe"))
add.class.node(fruits_class, "pear", states = c("yes", "no", "maybe"))

# Add node to inputs of its home class
set.node.input(fruits_class, c("apple", "banana"))

# Get inputs of class
inputs <- get.class.inputs(class)

# Add node to output of its home class
set.node.output(fruits_class, c("pear"))

# Get outputs of class
outputs <- get.class.outputs(class)

# Add node to outputs of its home class
write.rhc(fruits_class, "test.oobn")








