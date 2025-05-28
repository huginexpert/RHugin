get.class.outputs <- function(class) 
{
    nodes <- .Call(RHugin_class_get_outputs, class)
    nodes
}