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
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_adapt}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}


\examples{
demo("apple", echo = FALSE)

## Add experience and fading tables ##
get.table(apple, "Loses", type = "experience")
get.table(apple, "Loses", type = "fading")
summary(apple, nodes = "Loses")

## Delete the fading table ##
delete.table(apple, "Loses", type = "fading")
summary(apple, nodes = "Loses")

## Delete the experience table ##
delete.table(apple, "Loses", type = "experience")
summary(apple, nodes = "Loses")
}

\keyword{programming}


