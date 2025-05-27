hugin.class.collection.get.class.by_name <- function(cc, classname)
{
    c <- .Call(RHugin_cc_get_class_by_name, cc, classname)
    oldClass(c) <- "RHuginClass"
    c
}