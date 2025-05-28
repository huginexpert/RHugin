set.node.output <- function(class, nodes) {
    node.ptrs <- nodePointersFromNames(class, nodes)
    for (node in nodes) {
        if(is.null(node.ptrs[[node]]))
            stop(dQuote(node), "could not be found in the class")
        else
            .Call(RHugin_node_add_to_outputs, node.ptrs[[node]])
    }

    invisible()
}