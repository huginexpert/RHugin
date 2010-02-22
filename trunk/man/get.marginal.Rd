\name{get.marginal}
\alias{get.marginal}

\title{Get Marginal}

\description{
Compute the marginal table for the specified nodes with respect to the (imaginary) joint potential determined by the current potentials on the junction tree(s) of the domain. 
}

\usage{
get.marginal(domain, nodes, class = c("data.frame", "table", "ftable", "numeric"))
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{nodes}{a character vector specifying the names of the nodes in the marginal table.}
  \item{class}{a character string specifying a class for the output \code{table} component.}
}

\value{
a list with elements \code{table} and possibly \code{mean} and \code{cov}.  The \code{table} component is an object (whose class is determined by the \code{class} argument) that contains the discrete data in the table.  If there are one or more continuous nodes then the \code{mean} component will be a matrix where row i contains the mean for configuration i and the \code{cov} component will be a list where element i contains the variance-covariance matrix for configuration i.  If there are no continuous nodes then only the \code{table} component is returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_get_marginal}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\keyword{programming}


