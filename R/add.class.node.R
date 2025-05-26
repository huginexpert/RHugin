add.class.node <- function(class, name,
                     category = c("chance", "decision", "utility", "function"),
                     kind = c("discrete", "continuous", "other"),
                     subtype, states)
{
  if(name[1] %in% RHUGIN.RESERVED)
    stop("invalid name: ", dQuote(name[1]), " is a reserved word in RHugin")

  existingNode <- .Call(RHugin_class_get_node_by_name, class, name)
  if(!is.null(existingNode[[1]]))
    stop("Node ", dQuote(name[1]), " already exists")

  category <- match.arg(category)
  kind <- match.arg(kind)

  if(!missing(subtype))
    subtype <- match.arg(subtype, RHUGIN.SUBTYPES)
  else
    subtype <- NULL

  print(category)
  print(kind)
  
  node <- .Call(RHugin_class_new_node, class, category, kind)
  if(is.null(node))
    stop("node is null")
  
  print("R: node was not null")
  .Call(RHugin_node_set_name, c(node), name[1])
  print("???")

  if((category == "chance" && kind == "discrete") || category == "decision") {
    if(!is.null(subtype) && !missing(states))
      set.states(class, node = name, states = states, subtype = subtype)
    else if(!is.null(subtype))
      set.states(class, node = name, subtype = subtype)
    else if(!missing(states))
      set.states(class, node = name, states = states)
  }

  invisible()
}


