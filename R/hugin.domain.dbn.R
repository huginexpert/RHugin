hugin.domain.dbn <- function(class, number_of_slices)
{
    domain <- .Call(RHugin_class_create_dbn_domain, class, number_of_slices)
    oldClass(domain) <- "RHuginDomainDBN"
    domain
}