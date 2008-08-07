condense.data.frame <- function(data, indices)
{
  factors <- which(sapply(data, class) == "factor")
  for(idx in factors)
    data[[idx]] <- as.character(data[[idx]])

  indices <- indices[length(indices):1]
  x <- data[[length(data)]]
  indices <- as.list(data[indices])
  temp <- tapply(x, indices, sum)
  ans <- expand.grid.sans.coercion(dimnames(temp))
  ans <- ans[length(ans):1]
  temp <- as.vector(temp)
  temp[is.na(temp)] <- 0
  ans <- cbind(ans, temp, deparse.level = 0)
  names(ans)[length(ans)] <- "Freq"
  ans
}


