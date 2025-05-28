hugin.class.instance <- function(class1, class2, name = NULL) {
    node <- .Call(RHugin_class_new_instance, class1, class2)
    if(!is.null(name[1]))
        .Call(RHugin_node_set_name, node, name[1])
    
    invisible()
}