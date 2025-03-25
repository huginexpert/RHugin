set.class.name <- function(class, name)
{
    .Call(RHugin_class_set_name, class, name)
    invisible()
}