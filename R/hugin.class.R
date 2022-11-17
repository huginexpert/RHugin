hugin.class <- function(cc)
{
    class <- .Call(RHugin_cc_new_class, cc)
    oldClass(class) <- "RHuginClass"
    class
}