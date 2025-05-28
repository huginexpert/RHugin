hugin.class.instance <- function(class1, class2) {
    node.instance <- .Call(RHugin_class_new_instance, class1, class2)
    node.instance
}