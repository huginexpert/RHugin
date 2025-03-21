hugin.domain.dbn.move <- function(domain, delta)
{
    .Call(RHugin_domain_move_dbn_window, domain, delta)
    invisible()
}