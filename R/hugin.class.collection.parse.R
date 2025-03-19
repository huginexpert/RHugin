hugin.class.collection.parse <- function(file_name)
{
    cc <- .Call(RHugin_net_parse_classes, file_name)
    oldClass(cc) <- "RHuginClassCollection"
    cc
}