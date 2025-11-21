class.collection.get.members <- function(cc) {
  classes.ptrs <- .Call(RHugin_cc_get_members, cc)
  classes.ptrs
}
