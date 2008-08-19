condense.data.frame <- function(data, indices, class = c("data.frame", "table"))
{
  class <- match.arg(class)
  x <- data[[length(data)]]
  indices <- as.list(data[rev(indices)])
  table <- tapply(x, indices, sum)
  oldClass(table) <- "table"
  switch(class,
    "data.frame" = {
      table <- as.data.frame(table, stringsAsFactors = TRUE)
      row.names(table) <- NULL
      table
    },
    "table" = table)
}


