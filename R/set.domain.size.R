set.domain.size <- function(domain, width, height) {
    .Call(RHugin_domain_set_node_size, domain, c(width, height))
    invisible()
}