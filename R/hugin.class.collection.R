hugin.class.collection <- function()
{
    cc <- .Call(RHugin_new_class_collection)
    oldClass(cc) <- "RHuginClassCollection"
    cc
}