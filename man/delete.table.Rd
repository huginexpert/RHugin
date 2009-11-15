\name{delete.table}
\Rdversion{1.1}
\alias{delete.table}

\title{Delete Table}

\description{
Delete an experience or fading table from a node in an RHugin domain.
}

\usage{
delete.table(domain, node, type = c("experience", "fading"))
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{type}{a character string specifying the type of table to be deleted.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_domain_adapt}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}


\examples{
## Build the AppleTree example ##
demo("buildAppleTreeNetwork", echo = FALSE)

## Add experience and fading tables ##
get.table(AppleTree, "Loses", type = "experience")
get.table(AppleTree, "Loses", type = "fading")
summary(AppleTree, nodes = "Loses")

## Delete the fading table ##
delete.table(AppleTree, "Loses", type = "fading")
summary(AppleTree, nodes = "Loses")

## Delete the experience table ##
delete.table(AppleTree, "Loses", type = "experience")
summary(AppleTree, nodes = "Loses")
}

\keyword{programming}


