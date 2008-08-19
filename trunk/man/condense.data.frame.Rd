\name{condense.data.frame}
\alias{condense.data.frame}

\title{Condense a Data Frame}

\description{
Compute the marginal frequencies of a subset of factor variables in a data frame.  This function is internal to the \code{\link{generate.tables}} function and is therefore not terribly user friendly.  However, it may be useful in certain cases.
}

\usage{
condense.data.frame(data, indices, class = c("data.frame", "table"))
}

\arguments{
  \item{data}{a data frame containing multiple factor variables.}
  \item{indices}{a character vector specifying the names of the factor variables that should remain in the data frame.}
  \item{class}{a character string specifying the class of the returned object.}
}

\details{
The last variable in the data frame must be a numeric variable containing the probabilities or the counts.
}

\value{
a data frame or table.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{generate.tables}}.
}

\examples{
library(MASS)
data(housing)
condense.data.frame(housing, c("Type", "Cont"))
}

\keyword{programming}


