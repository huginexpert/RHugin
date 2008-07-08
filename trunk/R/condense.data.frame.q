condense.data.frame <- function(data, indices)
{
  indices <- indices[length(indices):1]
  x <- data[[length(data)]]
  indices <- as.list(data[indices])
  temp <- tapply(x, indices, sum, simplify = FALSE)
  ans <- expand.grid(dimnames(temp))
  ans <- ans[length(ans):1]
  temp <- unlist(temp)
  names(temp) <- NULL
  ans <- cbind(ans, temp, deparse.level = 0)
  names(ans)[length(ans)] <- "Freq"
  ans
}


