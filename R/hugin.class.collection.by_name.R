hugin.class.collection.by_name <- function(cc, name)
{
    cc <- .Call(RHugin_cc_get_class_by_name, cc, name)
    oldClass(cc) <- "RHuginClass"
    cc
}