\name{triangulate.RHuginDomain}
\alias{triangulate.RHuginDomain}

\title{Triangulate}

\description{
Triangulate a domain.
}

\usage{
\method{triangulate}{RHuginDomain}(object, method = "fill.in.weight", order, max.separators = 100000, ...)
}

\arguments{
  \item{object}{an RHugin domain.}
  \item{method}{a character string specifying the triangulation method. The choices are \code{"clique.size"}, \code{"clique.weight"}, \code{"fill.in.size"}, \code{"fill.in.weight"} and \code{"total.weight"}. The default, \code{"fill.in.weight"}, is the method used by the \code{compile} function when compiling a domain that has not been triangulated in advance.}
  \item{order}{a character vector specifying the elimination sequence (it must contain each chance and each decision node in the domain exactly once). If \code{order} is provided, it is used to triangulate the domain and the value of \code{method} is ignored.}
  \item{max.separators}{a positive integer value specifying the maximum number of minimal separators for the \code{total.weight} method.}
  \item{\dots}{additional arguments are ignored.}
}

\details{
The Triangulation section of the Compiling Domains chapter in the HUGIN API Reference Manual describes the triangulations methods in detail.
}

\value{
a character vector containing the node names in the order used to triangulate the domain.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{RHugin_domain_triangulate}, \code{RHugin_domain_triangulate_with_order}, \code{RHugin_domain_set_max_number_of_separators} and \code{RHugin_domain_get_elimination_order}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
\code{\link{compile.RHuginDomain}}.
}

\examples{
demo("asia", echo = FALSE)

# Triangulate the domain
elimination.order <- triangulate(asia, method = "clique.weight")

# Uncompiling removes the triangulation
uncompile(asia)

# Retriangulate using the elimination sequence from the previous triangulation
triangulate(asia, order = elimination.order)
}

\keyword{programming}


