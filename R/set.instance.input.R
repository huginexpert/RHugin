set.instance.input <- function(class, actualName, formalName)
{
    names <- unlist(str_split(formalName, "\\.", n = 2))
    instanceName <- names[1]
    instanceNode <- nodePointersFromNames(class, instanceName)
    instanceClass <- .Call(RHugin_node_get_instance_class, instanceNode)

    classFormalNodeName <- names[2]
    classFormalNode <- nodePointersFromNames(instanceClass, classFormalNodeName)

    actualNode <- nodePointersFromNames(class, actualName)

    .Call(RHugin_node_set_input, instanceNode, classFormalNode, actualNode)
    invisible()
}