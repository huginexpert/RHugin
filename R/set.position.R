set.position <- function(domain, node, x, y) {
    node.ptrs <- nodePointersFromNames(domain, node)
    .Call(RHugin_node_set_position, node.ptrs[node],
            c(x, y))
}