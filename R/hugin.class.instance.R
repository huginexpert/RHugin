hugin.class.instance <- function(classPeer, classToInstance, instanceName) {
    instance <- .Call(RHugin_class_new_instance, classPeer, classToInstance)
    .Call(RHugin_node_set_name, instance, instanceName)
    # if(!is.null(name[1]))
    #     .Call(RHugin_node_set_name, node, name[1])
    output.names <- get.class.outputs(classToInstance)
    node.ptrs <- nodePointersFromNames(classToInstance, output.names)

    for (name in output.names) {
        clone.ptr <- .Call(RHugin_node_get_output, instance[[1]], node.ptrs[[name]])
        new_clone_name <- paste(instanceName, name, sep = "_")
        .Call(RHugin_node_set_name, c(clone.ptr), new_clone_name)
    }

    invisible()
}