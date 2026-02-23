hugin.class.collection.parse <- function(net_string_or_file_name, class_collection = NULL)
{
    ccOrNull <- .Call(RHugin_net_parse_classes, net_string_or_file_name, class_collection)
    if (!is.null(ccOrNull)) {
        oldClass(ccOrNull) <- "RHuginClassCollection"
    }
    ccOrNull
}