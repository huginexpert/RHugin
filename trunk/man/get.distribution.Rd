\name{get.distribution}
\alias{get.distribution}

\title{Get Distribution}

\description{
Compute the distribution of a conditional Gaussian node.
}

\usage{
get.distribution(domain, node, class = c("data.frame", "table", "ftable", "numeric"))
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a conditional Gaussian node in \code{domain}.}
  \item{class}{a character string specifying a class for the output \code{table} component.}
}

\value{
a list with elements \code{table}, \code{mean} and \code{cov}.  The \code{table} component is an object (whose class is determined by the \code{class} argument) that contains the discrete data in the table, the \code{mean} component is a one-column matrix where row i contains the mean for configuration i and the \code{cov} component is a list where element i contains the variance for configuration i.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_node_get_distribution}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\keyword{programming}

