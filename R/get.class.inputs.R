get.class.inputs <- function(class) 
{
    nodes <- .Call(RHugin_class_get_inputs, class)
    nodes
}